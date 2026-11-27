
----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5302.48 | 0.0518674 | 6260.3ms | 10018896 | 30 | 2.62054e+07 | 1.80194e+06 | 0.223837 | 0.466895 | 1(Win) | true |
| Glaze | 3961.23 | 0.0497214 | 7443.77ms | 9930228 | 40 | 5.65203e+07 | 2.39072e+06 | 0.159545 | 0.624992 | 2(Loss) | true |
