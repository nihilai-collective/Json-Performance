
----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5846.21 | 0.196504 | 244.414ms | 14795 | 4890 | 109985 | 2413.46 | 0.025564 | 0.418793 | 1(Win) | true |
| Glaze | 3609.15 | 0.0442631 | 398.47ms | 14795 | 160 | 479.097 | 3909.4 | 0.00863229 | 0.681229 | 2(Loss) | true |
| simdjson (reflection) | 427.221 | 0.103927 | 3412.61ms | 14795 | 1280 | 1.50798e+06 | 33026.5 | 0.115843 | 5.79073 | 3(Loss) | true |
