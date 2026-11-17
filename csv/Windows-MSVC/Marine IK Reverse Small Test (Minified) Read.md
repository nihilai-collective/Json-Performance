
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 438.093 | 0.364037 | 1016.08ms | 4604 | 640 | 851941 | 10022.3 | 0.0576504 | 5.63011 | 1(Win) | true |
| Jsonifier (two-stage) | 427.756 | 0.267424 | 1050.19ms | 4604 | 2560 | 1.92894e+06 | 10264.5 | 0.138715 | 5.76674 | 2(Loss) | true |
| Glaze | 149.901 | 0.201471 | 2955.15ms | 4604 | 2560 | 8.91513e+06 | 29290.9 | 0.653712 | 16.4904 | 3(Loss) | true |
| simdjson (ondemand) | 97.1908 | 0.320052 | 4631.3ms | 4604 | 320 | 6.68978e+06 | 45176.2 | 0.0775344 | 25.456 | 4(Loss) | true |
