
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1063.51 | 0.185747 | 491.418ms | 4604 | 4890 | 287565 | 4128.51 | 0.126123 | 2.31334 | 1(Win) | true |
| Jsonifier (two-stage) | 970.21 | 0.0890814 | 536.42ms | 4604 | 30 | 487.568 | 4525.53 | 0.0875741 | 2.53673 | 2(Loss) | true |
| Glaze | 769.505 | 0.19664 | 668.002ms | 4604 | 30 | 3776.71 | 5705.9 | 0.228941 | 3.20384 | 3(Loss) | true |
| simdjson (ondemand) | 580.196 | 0.0974258 | 845.195ms | 4604 | 80 | 4348.69 | 7567.64 | 0.0563571 | 4.25144 | 4(Loss) | true |
