
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1141.92 | 0.827403 | 475.734ms | 4630 | 160 | 163774 | 3866.74 | 0.182657 | 2.15351 | 1(Win) | true |
| Jsonifier (two-stage) | 976.602 | 0.0798386 | 541.537ms | 4630 | 30 | 390.907 | 4521.3 | 0.528018 | 2.51949 | 2(Loss) | true |
| Glaze | 835.923 | 0.201063 | 616.82ms | 4630 | 40 | 4511.86 | 5282.2 | 0.460888 | 2.94646 | 3(Loss) | true |
| simdjson (reflection) | 822.278 | 0.0825949 | 649.505ms | 4630 | 40 | 786.849 | 5369.85 | 0.315275 | 2.99589 | 4(Loss) | true |
| simdjson (ondemand) | 793.692 | 0.164406 | 675.192ms | 4630 | 160 | 13384.9 | 5563.26 | 0.320192 | 3.1046 | 5(Loss) | true |
