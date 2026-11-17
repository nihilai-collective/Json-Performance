
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1049.71 | 0.155308 | 445.584ms | 4857 | 640 | 30058.7 | 4412.66 | 0.0177079 | 2.88031 | 1(Win) | true |
| Glaze | 851.959 | 0.211713 | 558.325ms | 4857 | 320 | 42397.7 | 5436.88 | 0.0689259 | 3.55065 | 2(Loss) | true |
| Jsonifier (two-stage) | 804.341 | 0.232981 | 585.898ms | 4857 | 320 | 57603.4 | 5758.75 | 0.162531 | 3.76524 | 3(Loss) | true |
| simdjson (ondemand) | 650.847 | 0.230473 | 730.791ms | 4857 | 160 | 43046.8 | 7116.88 | 0.00878272 | 4.65596 | 4(Loss) | true |
