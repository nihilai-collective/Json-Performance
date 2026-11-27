
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1645.5 | 0.0478713 | 290.799ms | 4918 | 40 | 74.4718 | 2850.3 | 0.093645 | 1.48992 | 1(Win) | true |
| simdjson (reflection) | 1547.45 | 0.0599117 | 307.175ms | 4918 | 30 | 98.9207 | 3030.9 | 0.208292 | 1.58635 | 2(Loss) | true |
| Glaze | 1133.52 | 0.14108 | 393.555ms | 4604 | 30 | 895.913 | 3873.53 | 0.0146271 | 2.16817 | 3(Loss) | true |
