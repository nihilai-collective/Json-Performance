
----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5288.81 | 0.498443 | 1001.08ms | 14795 | 40 | 7073.02 | 2667.82 | 0.130086 | 0.97071 | 2.98946 | 0.275769 | 0.000307536 | 1.01386e-05 | 0 | 1(Win) | true |
| Glaze | 3358.25 | 0.0841109 | 1153.85ms | 14795 | 4890 | 61068.6 | 4201.48 | 0.0870924 | 1.54098 | 4.4613 | 0.536195 | 0.000998735 | 3.1321e-05 | 1.40157e-05 | 2(Loss) | true |
