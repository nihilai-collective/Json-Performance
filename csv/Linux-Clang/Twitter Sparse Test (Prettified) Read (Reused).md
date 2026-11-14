
----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8188.66 | 0.199948 | 4997.97ms | 360584 | 40 | 282020 | 41994.6 | 0.130405 | 0.62003 | 2.94082 | 0.35907 | 0.000713703 | 5.54656e-06 | 3.32793e-06 | 1(Win) | true |
| simdjson (ondemand) | 7492.1 | 0.0389456 | 5395.47ms | 360584 | 2560 | 818019 | 45899 | 0.0323466 | 0.677308 | 3.13621 | 0.322126 | 0.000791206 | 1.7918e-06 | 7.84318e-07 | 2(Loss) | true |
