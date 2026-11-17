
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 661.397 | 0.459875 | 831.726ms | 4604 | 1280 | 1.19299e+06 | 6638.55 | 1.04964 | 1(Win) | true |
| Jsonifier (two-stage) | 561.347 | 0.404901 | 968.112ms | 4604 | 1280 | 1.28385e+06 | 7821.75 | 1.94699 | 2(Loss) | true |
| Glaze | 380.706 | 0.921483 | 1334.77ms | 4604 | 640 | 7.22845e+06 | 11533.1 | 0.71657 | 3(Loss) | true |
| simdjson (ondemand) | 358.779 | 0.152 | 1385.07ms | 4604 | 4890 | 1.69205e+06 | 12238 | 3.68441 | 4(Loss) | true |
