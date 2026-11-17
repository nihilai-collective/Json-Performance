
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2629.58 | 0.0775416 | 6982.09ms | 183677 | 160 | 426899 | 66614.4 | 0.032849 | 1.15543 | 1(Win) | true |
| Jsonifier | 2441.38 | 0.0508658 | 7464.17ms | 183677 | 640 | 852457 | 71749.7 | 0.00130664 | 1.24453 | 2(Loss) | true |
| Glaze | 2010.07 | 0.0284843 | 9021.99ms | 183677 | 2560 | 1.57739e+06 | 87145.2 | 0.116408 | 1.51166 | 3(Loss) | true |
| simdjson (ondemand) | 1539.5 | 0.353682 | 5985.85ms | 183677 | 80 | 1.29559e+07 | 113782 | 0.0483145 | 1.97391 | 4(Loss) | true |
