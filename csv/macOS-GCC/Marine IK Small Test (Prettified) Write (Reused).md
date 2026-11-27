
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9848.5 | 0.421559 | 245.731ms | 24893 | 2560 | 264345 | 2410.5 | 0.53231 | 1(Win) | true |
| Glaze | 3801.67 | 0.228758 | 639.566ms | 24579 | 1280 | 254649 | 6165.8 | 0.00973204 | 2(Loss) | true |
| simdjson (reflection) | 290.046 | 0.127438 | 8295.9ms | 24893 | 4890 | 5.32024e+07 | 81848.5 | 0.0248692 | 3(Loss) | true |
