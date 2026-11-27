
----
### Instruments Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 656.68 | 0.0456131 | 8411.99ms | 108313 | 2560 | 1.31787e+07 | 157299 | 0.0466573 | 7.722 | 36.5094 | 7.23069 | 0.00984179 | 5.69386e-05 | 3.55199e-05 | 1(Win) | true |
| simdjson (ondemand) | 248.261 | 0.0602857 | 5386.96ms | 108313 | 320 | 2.01337e+07 | 416075 | 0.393631 | 20.5199 | 90.5351 | 18.4057 | 0.0874526 | 0.000117743 | 9.84127e-05 | 2(Loss) | true |
