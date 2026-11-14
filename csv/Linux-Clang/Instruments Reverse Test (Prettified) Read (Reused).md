
----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1002.5 | 0.023503 | 9380.27ms | 183677 | 2560 | 4.31742e+06 | 174731 | 0.0946097 | 5.10718 | 23.7295 | 4.69105 | 0.00524691 | 1.91615e-05 | 7.8709e-06 | 1(Win) | true |
| simdjson (ondemand) | 432.395 | 0.0932883 | 5267.68ms | 183677 | 640 | 9.14077e+07 | 405111 | 0.000547692 | 11.8099 | 58.3182 | 10.4665 | 0.0367652 | 3.4512e-05 | 1.46061e-05 | 2(Loss) | true |
