import configparser
import os
import sys
import tkinter as tk
from tkinter import filedialog, messagebox, ttk


FONT_KEYS = [
    ("small_font", "Small font"),
    ("normal_font", "Normal font"),
    ("large_font", "Large font"),
    ("bold_font", "Bold font"),
    ("title_font", "Title font"),
    ("default_font", "Default font"),
]

SIZE_KEYS = [
    ("small_size", "Small size"),
    ("normal_size", "Normal size"),
    ("large_size", "Large size"),
    ("bold_size", "Bold size"),
    ("title_size", "Title size"),
    ("default_size", "Default size"),
]

LINE_HEIGHT_KEYS = [
    ("small_line_height", "Small line height"),
    ("normal_line_height", "Normal line height"),
    ("large_line_height", "Large line height"),
    ("bold_line_height", "Bold line height"),
    ("title_line_height", "Title line height"),
    ("default_line_height", "Default line height"),
]

KOREAN_PRESET = {
    "system.language": "korean",
    "font.ttf_renderer": "1",
    "font.gdi_renderer": "-1",
    "font.legacy_codepage": "949",
    "font.font_path": "fonts/korean",
    "font.fallback_font_path": "data/fonts/korean",
    "font.small_font": "NanumSquareNeo-aLt.ttf",
    "font.normal_font": "NanumSquareNeo-aLt.ttf",
    "font.large_font": "ChungjuKimSaeng.ttf",
    "font.bold_font": "ChungjuKimSaeng.ttf",
    "font.title_font": "ChungjuKimSaeng.ttf",
    "font.default_font": "ChungjuKimSaeng.ttf",
    "font.small_size": "16",
    "font.normal_size": "10",
    "font.large_size": "17",
    "font.bold_size": "13",
    "font.title_size": "22",
    "font.default_size": "13",
    "font.small_line_height": "16",
    "font.normal_line_height": "10",
    "font.large_line_height": "17",
    "font.bold_line_height": "13",
    "font.title_line_height": "22",
    "font.default_line_height": "13",
    "font.width_scale": "1.000000",
    "font.baseline_offset": "0",
    "font.antialiased": "1",
}

KOREAN_GDI_PRESET = {
    **KOREAN_PRESET,
    "font.ttf_renderer": "0",
    "font.gdi_renderer": "1",
    "font.legacy_codepage": "949",
    "font.gdi_text_face": "Dotum",
    "font.gdi_text_size": "11",
    "font.gdi_text_weight": "400",
    "font.gdi_text_line_height": "11",
    "font.gdi_button_face": "Cafe24 Ohsquare air Light",
    "font.gdi_button_size": "16",
    "font.gdi_button_weight": "700",
    "font.gdi_button_line_height": "20",
    "font.gdi_title_face": "Cafe24 Ohsquare air Light",
    "font.gdi_title_size": "16",
    "font.gdi_title_weight": "700",
    "font.gdi_title_line_height": "20",
    "font.gdi_binary_threshold": "128",
}

DEFAULTS = {
    "system.language": "english",
    "font.ttf_renderer": "0",
    "font.gdi_renderer": "0",
    "font.legacy_codepage": "0",
    "font.font_path": "fonts/english",
    "font.fallback_font_path": "data/fonts/english",
    "font.small_font": "",
    "font.normal_font": "",
    "font.large_font": "",
    "font.bold_font": "",
    "font.title_font": "",
    "font.default_font": "",
    "font.small_size": "16",
    "font.normal_size": "10",
    "font.large_size": "17",
    "font.bold_size": "13",
    "font.title_size": "22",
    "font.default_size": "13",
    "font.small_line_height": "16",
    "font.normal_line_height": "10",
    "font.large_line_height": "17",
    "font.bold_line_height": "13",
    "font.title_line_height": "22",
    "font.default_line_height": "13",
    "font.width_scale": "1.000000",
    "font.baseline_offset": "0",
    "font.antialiased": "1",
    "font.gdi_text_face": "Dotum",
    "font.gdi_text_size": "11",
    "font.gdi_text_weight": "400",
    "font.gdi_text_line_height": "11",
    "font.gdi_button_face": "Cafe24 Ohsquare air Light",
    "font.gdi_button_size": "16",
    "font.gdi_button_weight": "700",
    "font.gdi_button_line_height": "20",
    "font.gdi_title_face": "Cafe24 Ohsquare air Light",
    "font.gdi_title_size": "16",
    "font.gdi_title_weight": "700",
    "font.gdi_title_line_height": "20",
    "font.gdi_binary_threshold": "128",
}

CODEPAGE_PRESETS = {
    "Custom / manual input": "",
    "Korean CP949 / EUC-KR": "949",
    "Japanese Shift-JIS": "932",
    "Simplified Chinese GBK": "936",
    "Traditional Chinese Big5": "950",
    "Central European": "1250",
    "Cyrillic": "1251",
    "Western European": "1252",
    "Disabled / default": "0",
}

RENDERER_VALUES = {
    "Auto (Korean uses GDI)": ("0", "0"),
    "Disabled (use .fon/.aaf)": ("0", "-1"),
    "Legacy GDI (Windows)": ("0", "1"),
    "Enabled (use TTF)": ("1", "-1"),
    "TTF Auto": ("-1", "-1"),
}


def app_dir():
    if getattr(sys, "frozen", False):
        return os.path.dirname(sys.executable)
    return os.getcwd()


def ensure_section(config, section):
    if not config.has_section(section):
        config.add_section(section)


def get_value(config, section, key, default=""):
    if config.has_option(section, key):
        return config.get(section, key)
    return default


def set_value(config, dotted_key, value):
    section, key = dotted_key.split(".", 1)
    ensure_section(config, section)
    config.set(section, key, value)


class ConfigEditor(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("F.I.S.S.I.O.N. Font Config Editor")
        self.geometry("760x680")
        self.minsize(720, 620)

        self.config_path = tk.StringVar(value="")
        self.vars = {key: tk.StringVar(value=value) for key, value in DEFAULTS.items()}
        self.renderer_choice = tk.StringVar()
        self.codepage_choice = tk.StringVar()

        self._build_ui()
        self._sync_choices()

    def _build_ui(self):
        root = ttk.Frame(self, padding=12)
        root.pack(fill=tk.BOTH, expand=True)

        file_row = ttk.Frame(root)
        file_row.pack(fill=tk.X)
        ttk.Label(file_row, text="Config file").pack(side=tk.LEFT)
        ttk.Entry(file_row, textvariable=self.config_path).pack(side=tk.LEFT, fill=tk.X, expand=True, padx=8)
        ttk.Button(file_row, text="Browse", command=self.browse_config).pack(side=tk.LEFT)
        ttk.Button(file_row, text="Load", command=self.load_config).pack(side=tk.LEFT, padx=(8, 0))

        notebook = ttk.Notebook(root)
        notebook.pack(fill=tk.BOTH, expand=True, pady=12)

        basic = ttk.Frame(notebook, padding=12)
        fonts = ttk.Frame(notebook, padding=12)
        layout = ttk.Frame(notebook, padding=12)
        gdi = ttk.Frame(notebook, padding=12)
        notebook.add(basic, text="Basic")
        notebook.add(fonts, text="Fonts")
        notebook.add(layout, text="Layout")
        notebook.add(gdi, text="Legacy GDI")

        self._build_basic_tab(basic)
        self._build_fonts_tab(fonts)
        self._build_layout_tab(layout)
        self._build_gdi_tab(gdi)

        button_row = ttk.Frame(root)
        button_row.pack(fill=tk.X)
        ttk.Button(button_row, text="Korean GDI preset", command=self.apply_korean_gdi_preset).pack(side=tk.LEFT)
        ttk.Button(button_row, text="Korean TTF preset", command=self.apply_korean_preset).pack(side=tk.LEFT, padx=8)
        ttk.Button(button_row, text="Disable custom fonts", command=self.disable_custom_fonts).pack(side=tk.LEFT, padx=8)
        ttk.Button(button_row, text="Save", command=self.save_config).pack(side=tk.RIGHT)

    def _build_basic_tab(self, parent):
        self._add_entry(parent, "Language", self.vars["system.language"], 0)

        ttk.Label(parent, text="Font renderer").grid(row=1, column=0, sticky=tk.W, pady=6)
        renderer = ttk.Combobox(parent, textvariable=self.renderer_choice, state="readonly")
        renderer["values"] = list(RENDERER_VALUES.keys())
        renderer.grid(row=1, column=1, sticky=tk.EW, pady=6)
        renderer.bind("<<ComboboxSelected>>", self._renderer_selected)

        ttk.Label(parent, text="Legacy codepage").grid(row=2, column=0, sticky=tk.W, pady=6)
        codepage = ttk.Combobox(parent, textvariable=self.codepage_choice, state="readonly")
        codepage["values"] = list(CODEPAGE_PRESETS.keys())
        codepage.grid(row=2, column=1, sticky=tk.EW, pady=6)
        codepage.bind("<<ComboboxSelected>>", self._codepage_selected)

        self._add_entry(parent, "Codepage number", self.vars["font.legacy_codepage"], 3)
        self._add_folder_entry(parent, "Font path", self.vars["font.font_path"], 4)
        self._add_folder_entry(parent, "Fallback font path", self.vars["font.fallback_font_path"], 5)

        note = (
            "Legacy GDI reproduces the crisp Windows font path used by the old Korean patch. "
            "TTF remains available for cross-platform packages."
        )
        ttk.Label(parent, text=note, wraplength=560, foreground="#555").grid(
            row=6, column=0, columnspan=3, sticky=tk.W, pady=(16, 0)
        )

        parent.columnconfigure(1, weight=1)

    def _build_fonts_tab(self, parent):
        for index, (key, label) in enumerate(FONT_KEYS):
            self._add_file_entry(parent, label, self.vars[f"font.{key}"], index)

        parent.columnconfigure(1, weight=1)

    def _build_layout_tab(self, parent):
        ttk.Label(parent, text="Render size").grid(row=0, column=1, sticky=tk.W)
        ttk.Label(parent, text="Line height").grid(row=0, column=2, sticky=tk.W)

        for index, ((size_key, label), (line_key, _)) in enumerate(zip(SIZE_KEYS, LINE_HEIGHT_KEYS), start=1):
            ttk.Label(parent, text=label.replace(" size", "")).grid(row=index, column=0, sticky=tk.W, pady=4)
            ttk.Entry(parent, textvariable=self.vars[f"font.{size_key}"], width=12).grid(row=index, column=1, sticky=tk.W, padx=(0, 16), pady=4)
            ttk.Entry(parent, textvariable=self.vars[f"font.{line_key}"], width=12).grid(row=index, column=2, sticky=tk.W, pady=4)

        self._add_entry(parent, "Width scale", self.vars["font.width_scale"], 8)
        self._add_entry(parent, "Baseline offset", self.vars["font.baseline_offset"], 9)

        ttk.Label(parent, text="Antialiased").grid(row=10, column=0, sticky=tk.W, pady=6)
        ttk.Checkbutton(
            parent,
            variable=self.vars["font.antialiased"],
            onvalue="1",
            offvalue="0",
        ).grid(row=10, column=1, sticky=tk.W, pady=6)

    def _build_gdi_tab(self, parent):
        fields = [
            ("Text face", "gdi_text_face"),
            ("Text size", "gdi_text_size"),
            ("Text weight", "gdi_text_weight"),
            ("Text line height", "gdi_text_line_height"),
            ("Button face", "gdi_button_face"),
            ("Button size", "gdi_button_size"),
            ("Button weight", "gdi_button_weight"),
            ("Button line height", "gdi_button_line_height"),
            ("Title face", "gdi_title_face"),
            ("Title size", "gdi_title_size"),
            ("Title weight", "gdi_title_weight"),
            ("Title line height", "gdi_title_line_height"),
            ("Binary threshold", "gdi_binary_threshold"),
        ]
        for row, (label, key) in enumerate(fields):
            self._add_entry(parent, label, self.vars[f"font.{key}"], row)

        note = (
            "Threshold 1 matches the old DLL: every non-black GDI pixel becomes a solid Fallout palette pixel. "
            "Raise it if strokes look too heavy."
        )
        ttk.Label(parent, text=note, wraplength=560, foreground="#555").grid(
            row=len(fields), column=0, columnspan=3, sticky=tk.W, pady=(16, 0)
        )
        parent.columnconfigure(1, weight=1)

    def _add_entry(self, parent, label, variable, row):
        ttk.Label(parent, text=label).grid(row=row, column=0, sticky=tk.W, pady=6)
        ttk.Entry(parent, textvariable=variable).grid(row=row, column=1, sticky=tk.EW, pady=6)

    def _add_folder_entry(self, parent, label, variable, row):
        self._add_entry(parent, label, variable, row)
        ttk.Button(parent, text="Browse", command=lambda: self.browse_folder(variable)).grid(row=row, column=2, padx=(8, 0), pady=6)

    def _add_file_entry(self, parent, label, variable, row):
        self._add_entry(parent, label, variable, row)
        ttk.Button(parent, text="Browse", command=lambda: self.browse_font_file(variable)).grid(row=row, column=2, padx=(8, 0), pady=6)

    def browse_config(self):
        path = filedialog.askopenfilename(
            title="Select fission.cfg",
            initialdir=self._config_dir(),
            filetypes=[("FISSION config", "fission.cfg"), ("INI files", "*.cfg *.ini"), ("All files", "*.*")],
        )
        if path:
            self.config_path.set(path)
            self.load_config()

    def browse_folder(self, variable):
        path = filedialog.askdirectory(title="Select folder", initialdir=self._config_dir())
        if path:
            variable.set(self._relative_or_absolute(path))

    def browse_font_file(self, variable):
        path = filedialog.askopenfilename(
            title="Select TTF font",
            initialdir=self._config_dir(),
            filetypes=[("TrueType fonts", "*.ttf"), ("OpenType fonts", "*.otf"), ("All files", "*.*")],
        )
        if path:
            variable.set(os.path.basename(path))

    def _relative_or_absolute(self, path):
        try:
            return os.path.relpath(path, self._config_dir())
        except ValueError:
            return path

    def _config_dir(self):
        path = self.config_path.get().strip()
        if path:
            return os.path.dirname(path) or app_dir()
        return app_dir()

    def load_config(self, show_errors=True):
        path = self.config_path.get().strip()
        if not path:
            if show_errors:
                messagebox.showinfo("Select config", "Choose a fission.cfg file first.")
            self._sync_choices()
            return

        if not os.path.exists(path):
            if show_errors:
                messagebox.showerror("Config not found", f"Cannot find:\n{path}")
            self._sync_choices()
            return

        config = configparser.ConfigParser()
        config.optionxform = str
        try:
            with open(path, "r", encoding="utf-8-sig") as stream:
                config.read_file(stream)
        except UnicodeDecodeError:
            with open(path, "r", encoding="cp949") as stream:
                config.read_file(stream)
        except Exception as err:
            messagebox.showerror("Load failed", str(err))
            return

        for dotted_key, default in DEFAULTS.items():
            section, key = dotted_key.split(".", 1)
            self.vars[dotted_key].set(get_value(config, section, key, default))

        self._sync_choices()

    def save_config(self):
        if not self._validate():
            return

        path = self.config_path.get().strip()
        if not path:
            path = filedialog.asksaveasfilename(
                title="Save fission.cfg",
                initialdir=app_dir(),
                initialfile="fission.cfg",
                filetypes=[("FISSION config", "fission.cfg"), ("INI files", "*.cfg *.ini"), ("All files", "*.*")],
            )
            if not path:
                return
            self.config_path.set(path)

        config = configparser.ConfigParser()
        config.optionxform = str

        if os.path.exists(path):
            try:
                with open(path, "r", encoding="utf-8-sig") as stream:
                    config.read_file(stream)
            except UnicodeDecodeError:
                with open(path, "r", encoding="cp949") as stream:
                    config.read_file(stream)
            except Exception as err:
                messagebox.showerror("Load failed", str(err))
                return

        for dotted_key, variable in self.vars.items():
            set_value(config, dotted_key, variable.get().strip())

        try:
            with open(path, "w", encoding="utf-8", newline="\n") as stream:
                config.write(stream)
        except Exception as err:
            messagebox.showerror("Save failed", str(err))
            return

        messagebox.showinfo("Saved", f"Saved:\n{path}")

    def apply_korean_preset(self):
        for dotted_key, value in KOREAN_PRESET.items():
            self.vars[dotted_key].set(value)
        self._sync_choices()

    def apply_korean_gdi_preset(self):
        for dotted_key, value in KOREAN_GDI_PRESET.items():
            self.vars[dotted_key].set(value)
        self._sync_choices()

    def disable_custom_fonts(self):
        self.vars["font.ttf_renderer"].set("0")
        self.vars["font.gdi_renderer"].set("-1")
        self.vars["font.legacy_codepage"].set("0")
        self._sync_choices()

    def _renderer_selected(self, _event=None):
        label = self.renderer_choice.get()
        ttf_value, gdi_value = RENDERER_VALUES.get(label, ("0", "0"))
        self.vars["font.ttf_renderer"].set(ttf_value)
        self.vars["font.gdi_renderer"].set(gdi_value)

    def _codepage_selected(self, _event=None):
        label = self.codepage_choice.get()
        value = CODEPAGE_PRESETS.get(label, "")
        if value:
            self.vars["font.legacy_codepage"].set(value)

    def _sync_choices(self):
        renderer_value = (
            self.vars["font.ttf_renderer"].get(),
            self.vars["font.gdi_renderer"].get(),
        )
        for label, value in RENDERER_VALUES.items():
            if value == renderer_value:
                self.renderer_choice.set(label)
                break
        else:
            self.renderer_choice.set("Auto (Korean uses GDI)")

        codepage_value = self.vars["font.legacy_codepage"].get()
        for label, value in CODEPAGE_PRESETS.items():
            if value == codepage_value:
                self.codepage_choice.set(label)
                break
        else:
            self.codepage_choice.set("Custom / manual input")

    def _validate(self):
        int_keys = [key for key, _ in SIZE_KEYS + LINE_HEIGHT_KEYS]
        int_keys.extend([
            "legacy_codepage",
            "baseline_offset",
            "ttf_renderer",
            "gdi_renderer",
            "gdi_text_size",
            "gdi_text_weight",
            "gdi_text_line_height",
            "gdi_button_size",
            "gdi_button_weight",
            "gdi_button_line_height",
            "gdi_title_size",
            "gdi_title_weight",
            "gdi_title_line_height",
            "gdi_binary_threshold",
        ])
        for key in int_keys:
            value = self.vars[f"font.{key}"].get().strip()
            try:
                int(value)
            except ValueError:
                messagebox.showerror("Invalid value", f"{key} must be an integer.")
                return False

        try:
            width_scale = float(self.vars["font.width_scale"].get().strip())
        except ValueError:
            messagebox.showerror("Invalid value", "width_scale must be a number.")
            return False

        if width_scale <= 0:
            messagebox.showerror("Invalid value", "width_scale must be greater than 0.")
            return False

        renderer = self.vars["font.ttf_renderer"].get().strip()
        if renderer == "1":
            normal = self.vars["font.normal_font"].get().strip()
            default = self.vars["font.default_font"].get().strip()
            if not normal and not default:
                messagebox.showerror("Missing font", "Set at least normal_font or default_font when TTF renderer is enabled.")
                return False

        if self.vars["font.gdi_renderer"].get().strip() == "1":
            threshold = int(self.vars["font.gdi_binary_threshold"].get().strip())
            if threshold < 1 or threshold > 255:
                messagebox.showerror("Invalid value", "gdi_binary_threshold must be between 1 and 255.")
                return False

        return True


if __name__ == "__main__":
    ConfigEditor().mainloop()
