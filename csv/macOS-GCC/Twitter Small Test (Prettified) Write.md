
----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13463.7 | 2.20699 | 32.961ms | 4300 | 4890 | 220963 | 304.582 | 1.39228 | 1(Win) | true |
| Glaze | 2603.35 | 0.988291 | 144.897ms | 4300 | 1280 | 310207 | 1575.2 | 4.60271 | 2(Loss) | true |
| simdjson (reflection) | 352.06 | 1.1578 | 1127.84ms | 4300 | 160 | 2.90996e+06 | 11648 | 1.16753 | 3(Loss) | true |
