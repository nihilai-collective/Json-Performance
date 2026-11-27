
----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3064.92 | 0.0351609 | 848.049ms | 3770 | 4890 | 831.903 | 1173.06 | 0.232739 | 1.73822 | 6.76631 | 1.09735 | 0.00026574 | 4.23101e-05 | 1.08488e-05 | 1(Win) | true |
| simdjson (ondemand) | 2712.92 | 0.0679346 | 856.293ms | 3770 | 2560 | 2075.07 | 1325.27 | 0.0658923 | 1.95774 | 7.47162 | 1.08833 | 0.000455073 | 7.91611e-05 | 3.34673e-05 | 2(Loss) | true |
