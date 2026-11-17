
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1477.05 | 0.478469 | 162.572ms | 2158 | 30 | 1333.33 | 1393.33 | 0 | 2.0283 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1472.9 | 0.109329 | 164.517ms | 2158 | 1280 | 2987.04 | 1397.27 | 0.0727395 | 2.0374 | 1(Tie) | true |
| Jsonifier | 1252.18 | 0.122583 | 196.505ms | 2158 | 4890 | 19849.1 | 1643.56 | 0.0121037 | 2.39975 | 3(Loss) | true |
| simdjson (ondemand) | 1031.96 | 0.14531 | 222.43ms | 2158 | 1280 | 10749.3 | 1994.3 | 0.121588 | 2.91661 | 4(Loss) | true |
