
----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5326.18 | 0.103728 | 1006.42ms | 14795 | 2560 | 19329.8 | 2649.1 | 0.0599914 | 0.95389 | 2.97046 | 0.275701 | 0.000286758 | 7.65673e-06 | 7.12868e-07 | 1(Win) | true |
| Glaze | 3274.18 | 0.131917 | 1171.87ms | 14795 | 1280 | 41365.4 | 4309.36 | 0.216112 | 1.55897 | 4.4613 | 0.536195 | 0.000951705 | 2.83035e-05 | 1.20395e-05 | 2(Loss) | true |
