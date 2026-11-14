
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 653.205 | 0.139921 | 1723.17ms | 11812 | 4890 | 2.84723e+06 | 17245.4 | 0.150795 | 4.64686 | 1(Win) | true |
| simdjson (ondemand) | 575.526 | 0.0877611 | 1968.75ms | 11812 | 1280 | 377686 | 19573 | 0.161393 | 5.2747 | 2(Loss) | true |
