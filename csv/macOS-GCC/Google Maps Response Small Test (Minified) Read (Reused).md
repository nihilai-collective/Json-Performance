
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2058.83 | 0.301794 | 254.835ms | 4390 | 2560 | 96416.2 | 2033.5 | 0.601232 | 1(Win) | true |
| Jsonifier (two-stage) | 1397.78 | 0.627179 | 370.937ms | 4390 | 40 | 14115.4 | 2995.2 | 0 | 2(Loss) | true |
| Glaze | 1142.58 | 0.253674 | 418.774ms | 4390 | 4890 | 422493 | 3664.2 | 0.468944 | 3(Loss) | true |
| simdjson (reflection) | 1047.15 | 0.336472 | 448.058ms | 4390 | 4890 | 884942 | 3998.1 | 1.07959 | 4(Loss) | true |
| simdjson (ondemand) | 787.39 | 0.232522 | 589.301ms | 4390 | 2560 | 391308 | 5317.1 | 0.855463 | 5(Loss) | true |
