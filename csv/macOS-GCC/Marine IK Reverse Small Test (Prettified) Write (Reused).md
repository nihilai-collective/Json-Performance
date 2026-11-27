
----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9524.5 | 0.413788 | 267.207ms | 24893 | 2560 | 272312 | 2492.5 | 0.228164 | 1(Win) | true |
| Glaze | 3774.8 | 0.116839 | 628.025ms | 24579 | 4890 | 257411 | 6209.7 | 0.59229 | 2(Loss) | true |
| simdjson (reflection) | 323.845 | 0.0744042 | 7556.29ms | 24893 | 2560 | 7.61581e+06 | 73306.2 | 0.218602 | 3(Loss) | true |
