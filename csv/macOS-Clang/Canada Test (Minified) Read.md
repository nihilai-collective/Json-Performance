
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 636.788 | 0.682849 | 5168.32ms | 2251027 | 80 | 4.23947e+10 | 3.37121e+06 | 0.720616 | 1(Win) | true |
| Glaze STATISTICAL TIE | 511.901 | 1.73464 | 6383.75ms | 2251027 | 40 | 2.11674e+11 | 4.19367e+06 | 0.529327 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 505.59 | 0.451851 | 6842.45ms | 2251027 | 80 | 2.94473e+10 | 4.24602e+06 | 6.35221 | -(Tie) | false |
| Jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 501.681 | 1.12669 | 5766.45ms | 2251027 | 30 | 6.97331e+10 | 4.2791e+06 | 9.53401 | -(Tie) | false |
