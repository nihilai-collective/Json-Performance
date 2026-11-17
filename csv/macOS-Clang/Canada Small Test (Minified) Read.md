
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 587.589 | 0.315363 | 831.493ms | 4630 | 40 | 22464.5 | 7514.62 | 1.69722 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 585.376 | 0.530313 | 728.857ms | 4630 | 640 | 1.02408e+06 | 7543.03 | 0.0933764 | 1(Tie) | true |
| Glaze | 441.231 | 0.17238 | 982.744ms | 4630 | 40 | 11903.2 | 10007.2 | 0.190996 | 3(Loss) | true |
| simdjson (ondemand) | 409.816 | 0.240371 | 1092.14ms | 4630 | 4890 | 3.27987e+06 | 10774.4 | 0.0153589 | 4(Loss) | true |
