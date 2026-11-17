
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 708.647 | 0.208162 | 8141.35ms | 461466 | 80 | 1.33694e+08 | 621026 | 0.504466 | 3.49348 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 633.207 | 0.142874 | 8958.92ms | 461466 | 640 | 6.31066e+08 | 695015 | 1.02136 | 3.90972 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 630.43 | 0.267455 | 9155.98ms | 461466 | 30 | 1.04576e+08 | 698077 | 0.0539869 | 3.92689 | 2(Tie) | true |
| simdjson (ondemand) | 501 | 0.244775 | 5619.43ms | 461466 | 30 | 1.38695e+08 | 878420 | 0.14022 | 4.94147 | 4(Loss) | true |
