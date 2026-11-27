
----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4410.39 | 0.0903769 | 1056.03ms | 14795 | 4890 | 40879.1 | 3199.18 | 0.10882 | 1.16066 | 2.96715 | 0.270903 | 0.000283106 | 1.21912e-05 | 1.9351e-06 | 1(Win) | true |
| Glaze | 3735.24 | 0.0794134 | 1109.79ms | 14795 | 4890 | 44003.7 | 3777.43 | 0.358561 | 1.37412 | 4.24475 | 0.486786 | 0.00105835 | 1.39466e-05 | 3.26203e-06 | 2(Loss) | true |
