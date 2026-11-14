
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1436.06 | 0.182011 | 6502.93ms | 676745 | 160 | 1.07058e+08 | 449420 | 0.0656833 | 2.11601 | 1(Win) | true |
| simdjson (ondemand) | 1187.19 | 0.0849468 | 7702.96ms | 676745 | 640 | 1.36485e+08 | 543632 | 0.264115 | 2.55979 | 2(Loss) | true |
