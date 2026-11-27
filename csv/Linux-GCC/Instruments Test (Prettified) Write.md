
----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 32291.4 | 0.0504937 | 652.411ms | 213963 | 40 | 407.228 | 6319.05 | 0.128809 | 0.0763303 | 1(Win) | true |
| Glaze | 3608.02 | 0.064501 | 5675.98ms | 213963 | 2560 | 3.40654e+06 | 56554.9 | 0.094158 | 0.685865 | 2(Loss) | true |
| simdjson (reflection) | 511.516 | 0.12257 | 5161.02ms | 213963 | 320 | 7.65031e+07 | 398914 | 0.731064 | 4.83898 | 3(Loss) | true |
