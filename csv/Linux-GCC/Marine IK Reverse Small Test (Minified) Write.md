
----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1614.86 | 0.0461184 | 295.071ms | 4918 | 80 | 143.531 | 2904.39 | 0.0511894 | 1.5186 | 1(Win) | true |
| simdjson (reflection) | 1431.24 | 0.0471841 | 331.351ms | 4918 | 30 | 71.7241 | 3277 | 0.0223832 | 1.71551 | 2(Loss) | true |
| Glaze | 1064.97 | 0.126679 | 423.221ms | 4604 | 30 | 818.326 | 4122.87 | 0.0404086 | 2.30953 | 3(Loss) | true |
