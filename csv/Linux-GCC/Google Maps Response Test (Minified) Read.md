
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1997.28 | 0.0779685 | 570.285ms | 11812 | 30 | 580.133 | 5640.07 | 0.243496 | 1.23367 | 1(Win) | true |
| Glaze | 1746.29 | 0.133742 | 653.799ms | 11812 | 30 | 2232.91 | 6450.7 | 0.0625646 | 1.41187 | 2(Loss) | true |
| Jsonifier (two-stage) | 1606.86 | 0.0440694 | 712.81ms | 11812 | 40 | 381.789 | 7010.43 | 0.170871 | 1.53458 | 3(Loss) | true |
| simdjson (reflection) | 1441.13 | 0.0448651 | 809.122ms | 11812 | 80 | 983.897 | 7816.66 | 0.553898 | 1.712 | 4(Loss) | true |
| simdjson (ondemand) | 1145.68 | 0.102364 | 989.362ms | 11812 | 40 | 4052.1 | 9832.45 | 0.0894099 | 2.15498 | 5(Loss) | true |
