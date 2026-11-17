
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2096.84 | 0.800295 | 125.431ms | 2158 | 4890 | 301704 | 981.49 | 3.97144 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1824.12 | 0.489237 | 135.559ms | 2158 | 4890 | 148985 | 1128.23 | 1.66087 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1788.66 | 1.08927 | 143.834ms | 2158 | 2560 | 402126 | 1150.6 | 2.04325 | 2(Tie) | true |
| simdjson (ondemand) | 1572.94 | 1.40844 | 150ms | 2158 | 640 | 217338 | 1308.4 | 1.53522 | 4(Loss) | true |
| simdjson (reflection) | 1496.1 | 0.714445 | 162.317ms | 2158 | 2560 | 247264 | 1375.6 | 0.650007 | 5(Loss) | true |
