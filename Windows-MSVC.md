# Json-Performance: Correctness Validation (AVX512)
Correctness validation of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.52.37029.0 compiler).  

Latest results: (Nov 27, 2026)
#### Here are the commits we used:
----
| Jsonifier: [a1328b5](https://github.com/nihilai-collective/Jsonifier/commit/a1328b5)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX512` |
| simdjson (stage-1) | `icelake` |

>> In these tests we are comparing the 'json structural tape' that each library generates during its 'stage-1' parsing. We read the simdjson tape straight out of upstream simdjson's internal `dom_parser_implementation` after `stage1()`, no fork or patch needed.  


----
### Bool Test Structural Comparison

All **200** structurals across **200** elements match between Jsonifier and simdjson . ✅


----
### Double Test Structural Comparison

All **200** structurals across **200** elements match between Jsonifier and simdjson . ✅


----
### Int64 Test Structural Comparison

All **200** structurals across **200** elements match between Jsonifier and simdjson . ✅


----
### String Test Structural Comparison

All **200** structurals across **200** elements match between Jsonifier and simdjson . ✅


----
### Uint64 Test Structural Comparison

All **200** structurals across **200** elements match between Jsonifier and simdjson . ✅


----
### Apache Builds Test (Minified) Structural Comparison

All **12364** structurals match between Jsonifier and simdjson . ✅


----
### Apache Builds Test (Prettified) Structural Comparison

All **12364** structurals match between Jsonifier and simdjson . ✅


----
### Canada Test (Minified) Structural Comparison

All **334373** structurals match between Jsonifier and simdjson . ✅


----
### Canada Test (Prettified) Structural Comparison

All **334373** structurals match between Jsonifier and simdjson . ✅


----
### CitmCatalog Test (Minified) Structural Comparison

All **135990** structurals match between Jsonifier and simdjson . ✅


----
### CitmCatalog Test (Prettified) Structural Comparison

All **135990** structurals match between Jsonifier and simdjson . ✅


----
### Discord Test (Minified) Structural Comparison

All **13015** structurals match between Jsonifier and simdjson . ✅


----
### Discord Test (Prettified) Structural Comparison

All **13015** structurals match between Jsonifier and simdjson . ✅


----
### Github Events Test (Minified) Structural Comparison

All **4656** structurals match between Jsonifier and simdjson . ✅


----
### Github Events Test (Prettified) Structural Comparison

All **4656** structurals match between Jsonifier and simdjson . ✅


----
### Google Maps Response Test (Minified) Structural Comparison

All **3117** structurals match between Jsonifier and simdjson . ✅


----
### Google Maps Response Test (Prettified) Structural Comparison

All **3117** structurals match between Jsonifier and simdjson . ✅


----
### Instruments Test (Minified) Structural Comparison

All **27173** structurals match between Jsonifier and simdjson . ✅


----
### Instruments Test (Prettified) Structural Comparison

All **27173** structurals match between Jsonifier and simdjson . ✅


----
### Marine IK Test (Minified) Structural Comparison

All **643012** structurals match between Jsonifier and simdjson . ✅


----
### Marine IK Test (Prettified) Structural Comparison

All **643012** structurals match between Jsonifier and simdjson . ✅


----
### Random Test (Minified) Structural Comparison

All **88017** structurals match between Jsonifier and simdjson . ✅


----
### Random Test (Prettified) Structural Comparison

All **88017** structurals match between Jsonifier and simdjson . ✅


----
### Twitter Test (Minified) Structural Comparison

All **55263** structurals match between Jsonifier and simdjson . ✅


----
### Twitter Test (Prettified) Structural Comparison

All **55263** structurals match between Jsonifier and simdjson . ✅

