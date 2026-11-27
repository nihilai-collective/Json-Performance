
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1229.45 | 2.15914 | 984.831ms | 11812 | 40 | 1.56548e+06 | 9162.5 | 0.190632 | 2.46606 | 1(Win) | true |
| Jsonifier (two-stage) | 1009.86 | 0.806487 | 1112.69ms | 11812 | 4890 | 3.95753e+07 | 11154.8 | 1.0417 | 3.00284 | 2(Loss) | true |
| Glaze | 925.525 | 1.16919 | 1275.06ms | 11812 | 80 | 1.62005e+06 | 12171.2 | 1.59641 | 3.27786 | 3(Loss) | true |
| simdjson (ondemand) | 571.029 | 0.929345 | 2005.26ms | 11812 | 2560 | 8.60448e+07 | 19727.2 | 0.396005 | 5.31603 | 4(Loss) | true |
