
----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5902.72 | 0.509758 | 9921.76ms | 10018896 | 80 | 5.44696e+09 | 1.61871e+06 | 0.738292 | 0.41942 | 1(Win) | true |
| Glaze | 3756.65 | 0.066396 | 7901.69ms | 9930228 | 30 | 8.40471e+07 | 2.52092e+06 | 0.617836 | 0.659035 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 259.172 | 2.24844 | 11153.8ms | 10018896 | 30 | 2.06134e+13 | 3.68666e+07 | 3.38259 | 9.55266 | -(Loss) | false |
