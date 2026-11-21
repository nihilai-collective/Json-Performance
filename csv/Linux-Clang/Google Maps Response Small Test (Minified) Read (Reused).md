
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2700.49 | 0.0555425 | 175.071ms | 4390 | 160 | 118.636 | 1550.33 | 0.0395235 | 0.900794 | 1(Win) | true |
| Jsonifier (two-stage) | 2080.56 | 0.0372105 | 223.284ms | 4390 | 320 | 179.412 | 2012.27 | 0.0651121 | 1.1743 | 2(Loss) | true |
| Glaze | 1801.61 | 0.0949335 | 251.653ms | 4390 | 30 | 146.006 | 2323.83 | 0.0732085 | 1.35822 | 3(Loss) | true |
| simdjson (ondemand) | 1071.34 | 0.161152 | 431.843ms | 4390 | 2560 | 101528 | 3907.85 | 0.355031 | 2.2946 | 4(Loss) | true |
