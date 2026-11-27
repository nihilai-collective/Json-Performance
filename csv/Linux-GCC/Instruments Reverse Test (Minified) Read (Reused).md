
----
### Instruments Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 685.452 | 0.0252221 | 8178.78ms | 108313 | 2560 | 3.69835e+06 | 150697 | 0.108197 | 7.42162 | 35.8273 | 7.07308 | 0.00931837 | 2.09354e-05 | 1.31383e-05 | 1(Win) | true |
| simdjson (ondemand) | 252.151 | 0.11441 | 5377.83ms | 108313 | 80 | 1.75735e+07 | 409657 | 0.0452734 | 20.2012 | 89.8618 | 18.2495 | 0.0845914 | 0.000100865 | 7.74376e-05 | 2(Loss) | true |
