
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1988.28 | 0.27183 | 1009.43ms | 18245 | 1280 | 724330 | 8751.17 | 0.0847382 | 1.24119 | 1(Win) | true |
| Jsonifier | 1679.11 | 0.118127 | 1216.32ms | 18245 | 40 | 5993.59 | 10362.5 | 0.185305 | 1.4689 | 2(Loss) | true |
| Glaze | 645.004 | 0.380071 | 2911.17ms | 18245 | 160 | 1.68195e+06 | 26976.2 | 0.447458 | 3.83419 | 3(Loss) | true |
| simdjson (ondemand) | 406.366 | 0.199612 | 4552.32ms | 18245 | 640 | 4.67525e+06 | 42818 | 0.0346791 | 6.08873 | 4(Loss) | true |
