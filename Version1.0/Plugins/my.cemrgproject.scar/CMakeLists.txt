project(my_cemrgproject_scar)

mitk_create_plugin(
  EXPORT_DIRECTIVE SCAR_EXPORT
  EXPORTED_INCLUDE_SUFFIXES src
  MODULE_DEPENDS MitkQtWidgetsExt MyCemrgLib
)
