
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2480.95 | 0.08621 | 2475.95ms | 56369 | 2560 | 893307 | 21668.2 | 0.366523 | 0.996692 | 1(Win) | true |
| Jsonifier (two-stage) | 2059.55 | 0.0621764 | 2939.47ms | 56369 | 4890 | 1.28795e+06 | 26101.7 | 0.0279693 | 1.20091 | 2(Loss) | true |
| Glaze | 1936.69 | 0.108959 | 3068.64ms | 56369 | 30 | 27441.2 | 27757.4 | 0.573831 | 1.2772 | 3(Loss) | true |
| simdjson (reflection) | 1896.65 | 0.097625 | 3200.88ms | 56369 | 2560 | 1.96007e+06 | 28343.5 | 0.186807 | 1.30412 | 4(Loss) | true |
| simdjson (ondemand) | 1675.69 | 0.0555602 | 3575.91ms | 56369 | 4890 | 1.55357e+06 | 32080.9 | 0.544453 | 1.47626 | 5(Loss) | true |
