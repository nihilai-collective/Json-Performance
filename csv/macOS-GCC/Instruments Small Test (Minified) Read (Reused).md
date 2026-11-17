
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2819.24 | 0.843337 | 190.722ms | 4669 | 2560 | 454179 | 1579.4 | 1.3245 | 1(Win) | true |
| Jsonifier (two-stage) | 1718.4 | 0.614861 | 275.118ms | 4669 | 1280 | 324912 | 2591.2 | 0.0154345 | 2(Loss) | true |
| Glaze | 1600.8 | 0.279123 | 293.803ms | 4669 | 4890 | 294764 | 2781.55 | 0.441943 | 3(Loss) | true |
| simdjson (reflection) | 1271.47 | 0.481023 | 373.771ms | 4669 | 1280 | 363224 | 3502 | 0.297858 | 4(Loss) | true |
| simdjson (ondemand) | 1163.62 | 0.387958 | 400.019ms | 4669 | 1280 | 282102 | 3826.6 | 0.328193 | 5(Loss) | true |
