
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1361 | 0.211963 | 845.435ms | 11812 | 2560 | 787931 | 8276.84 | 0.094772 | 1.8091 | 1(Win) | true |
| Jsonifier (two-stage) | 1170.19 | 0.130245 | 979.126ms | 11812 | 4890 | 768722 | 9626.48 | 0.0332813 | 2.106 | 2(Loss) | true |
| Glaze | 874.88 | 0.131082 | 1315.95ms | 11812 | 4890 | 1.39298e+06 | 12875.8 | 0.155935 | 2.8197 | 3(Loss) | true |
| simdjson (ondemand) | 576.679 | 0.259179 | 1998.1ms | 11812 | 640 | 1.64043e+06 | 19533.9 | 0.138573 | 4.28337 | 4(Loss) | true |
