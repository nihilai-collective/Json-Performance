
----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2464.78 | 0.041059 | 496.176ms | 11812 | 80 | 281.706 | 4570.3 | 0.0257161 | 0.998795 | 1(Win) | true |
| Jsonifier (two-stage) | 1980.44 | 0.141688 | 607.35ms | 11812 | 4890 | 317614 | 5688.04 | 0.259034 | 1.24436 | 2(Loss) | true |
| Glaze | 1859.91 | 0.141401 | 642.677ms | 11812 | 2560 | 187761 | 6056.63 | 0.0270954 | 1.32538 | 3(Loss) | true |
| simdjson (ondemand) | 1054.04 | 0.176057 | 1112.48ms | 11812 | 1280 | 453163 | 10687.3 | 0.122403 | 2.34273 | 4(Loss) | true |
