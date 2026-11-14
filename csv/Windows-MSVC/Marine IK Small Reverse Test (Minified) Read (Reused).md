
----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 217.362 | 0.162185 | 2147.51ms | 4604 | 640 | 686917 | 20200 | 0.242295 | 13.9671 | 1(Win) | true |
| simdjson (ondemand) | 171.949 | 0.280495 | 2691.2ms | 4604 | 80 | 410405 | 25535 | 0.117624 | 17.6533 | 2(Loss) | true |
