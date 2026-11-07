
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2815.39 | 0.0563346 | 3684.72ms | 108313 | 4890 | 2.08902e+06 | 36689.5 | 0.169677 | 0.878759 | 1(Win) | true |
| Jsonifier (two-stage) | 2376.59 | 0.0618267 | 4351.97ms | 108313 | 4890 | 3.53114e+06 | 43463.7 | 0.0390132 | 1.04111 | 2(Loss) | true |
| Glaze | 1749.58 | 0.0806123 | 5998.43ms | 108313 | 640 | 1.4497e+06 | 59040.1 | 0.00375553 | 1.41447 | 3(Loss) | true |
| simdjson (ondemand) | 717.783 | 0.0837882 | 7369.13ms | 108313 | 1280 | 1.86102e+07 | 143909 | 0.0467539 | 3.4486 | 4(Loss) | true |
