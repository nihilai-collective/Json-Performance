
----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17589.7 | 0.0352 | 591.537ms | 108313 | 30 | 128.19 | 5872.5 | 0.039749 | 0.140098 | 1(Win) | true |
| simdjson (reflection) | 14191.1 | 0.0281094 | 728.789ms | 108313 | 80 | 334.905 | 7278.86 | 0.0530928 | 0.17381 | 2(Loss) | true |
| Glaze | 2394.04 | 0.0859529 | 4310.25ms | 108313 | 1280 | 1.76047e+06 | 43146.8 | 0.0404543 | 1.0335 | 3(Loss) | true |
