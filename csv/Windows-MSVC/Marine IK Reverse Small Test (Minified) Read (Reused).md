
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 560.917 | 0.0708256 | 908.993ms | 4604 | 4890 | 150302 | 7827.75 | 0.00328693 | 5.40519 | 1(Win) | true |
| Jsonifier | 409.64 | 0.139526 | 1198.79ms | 4604 | 2560 | 572550 | 10718.5 | 0.166999 | 7.40294 | 2(Loss) | true |
| Glaze | 329.63 | 0.117413 | 1449.66ms | 4604 | 640 | 156541 | 13320.2 | 0.104291 | 9.20598 | 3(Loss) | true |
| simdjson (ondemand) | 175.438 | 0.0760081 | 2651.86ms | 4604 | 1280 | 463182 | 25027.1 | 0.0246668 | 17.3097 | 4(Loss) | true |
