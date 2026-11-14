
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1700.32 | 0.31073 | 249.89ms | 4390 | 4890 | 286248 | 2462.26 | 0.00165274 | 1(Win) | true |
| Jsonifier (two-stage) | 1200.16 | 0.6887 | 349.585ms | 4390 | 640 | 369396 | 3488.4 | 0.681136 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 994.098 | 0.176371 | 419.238ms | 4390 | 4890 | 269796 | 4211.49 | 0.85251 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 962.001 | 1.78719 | 459.723ms | 4390 | 40 | 241979 | 4352 | 0.970874 | 3(Tie) | true |
| simdjson (ondemand) | 722.355 | 0.152379 | 586.914ms | 4390 | 4890 | 381404 | 5795.81 | 0.521634 | 5(Loss) | true |
