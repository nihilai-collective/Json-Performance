
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 569.576 | 0.126803 | 919.105ms | 4604 | 80 | 7643.99 | 7708.75 | 0.468044 | 4.32938 | 1(Win) | true |
| Jsonifier (two-stage) | 545.982 | 0.528224 | 956.532ms | 4604 | 640 | 1.15486e+06 | 8041.88 | 0.69651 | 4.51817 | 2(Loss) | true |
| Glaze | 176.662 | 0.454166 | 2700.05ms | 4604 | 160 | 2.0386e+06 | 24853.8 | 0.0502689 | 13.9966 | 3(Loss) | true |
| simdjson (ondemand) | 105.866 | 0.108632 | 4335.63ms | 4604 | 2560 | 5.19652e+06 | 41474.3 | 0.66682 | 23.3707 | 4(Loss) | true |
