
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1938.46 | 0.0373985 | 6782.38ms | 466906 | 640 | 4.72318e+06 | 229706 | 0.0687491 | 1.56779 | 1(Win) | true |
| Glaze | 1606.68 | 0.0791384 | 7995.92ms | 466906 | 80 | 3.84828e+06 | 277141 | 0.0410609 | 1.89162 | 2(Loss) | true |
| Jsonifier (two-stage) | 1531.65 | 0.160834 | 8349.11ms | 466906 | 320 | 6.99595e+07 | 290717 | 0.0232239 | 1.98425 | 3(Loss) | true |
| simdjson (ondemand) | 1166.59 | 0.209488 | 5229.28ms | 466906 | 160 | 1.02297e+08 | 381691 | 0.358946 | 2.6052 | 4(Loss) | true |
