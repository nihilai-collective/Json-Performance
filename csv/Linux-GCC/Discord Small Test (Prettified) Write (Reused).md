
----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15978.7 | 0.16312 | 763.423ms | 7376 | 1280 | 660.055 | 440.229 | 0.161932 | 0.35208 | 1.07335 | 0.161876 | 0.000135893 | 4.56506e-05 | 2.74327e-05 | 1(Win) | true |
| Glaze | 3922.64 | 0.131385 | 908.742ms | 7376 | 4890 | 27144.6 | 1793.26 | 0.259411 | 1.33525 | 3.79799 | 0.61307 | 0.00015745 | 4.45817e-05 | 2.08491e-05 | 2(Loss) | true |
| simdjson (reflection) | 524.764 | 0.129297 | 2086.05ms | 7376 | 1280 | 384507 | 13404.7 | 0.128519 | 9.76098 | 39.4227 | 8.03037 | 0.012254 | 0.000113014 | 6.16442e-05 | 3(Loss) | true |
