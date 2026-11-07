
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1123.85 | 0.0526017 | 475.103ms | 4604 | 80 | 337.867 | 3906.86 | 0.0776874 | 2.18807 | 1(Win) | true |
| Jsonifier (two-stage) | 997.815 | 0.198927 | 519.226ms | 4604 | 2560 | 196155 | 4400.33 | 0.064717 | 2.46603 | 2(Loss) | true |
| Glaze | 765.747 | 0.184676 | 655.788ms | 4604 | 30 | 3363.89 | 5733.9 | 0.00465092 | 3.21907 | 3(Loss) | true |
| simdjson (ondemand) | 586.744 | 0.10217 | 828.978ms | 4604 | 4890 | 285844 | 7483.19 | 0.370693 | 4.20288 | 4(Loss) | true |
