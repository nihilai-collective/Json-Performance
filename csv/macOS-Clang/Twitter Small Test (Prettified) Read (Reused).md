
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2354.81 | 0.199317 | 175.542ms | 3808 | 4890 | 46204 | 1542.2 | 0.833859 | 1(Win) | true |
| Glaze | 2206.49 | 0.337493 | 188.096ms | 3808 | 30 | 925.637 | 1645.87 | 0 | 2(Loss) | true |
| Jsonifier | 2020.15 | 0.51597 | 186.131ms | 3808 | 1280 | 110125 | 1797.68 | 0.973873 | 3(Loss) | true |
| simdjson (ondemand) | 1116.69 | 0.199916 | 372.842ms | 3808 | 40 | 1690.76 | 3252.1 | 0.952275 | 4(Loss) | true |
