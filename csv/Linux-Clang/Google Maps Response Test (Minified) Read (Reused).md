
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2772.96 | 0.049406 | 441.582ms | 11812 | 80 | 322.263 | 4062.38 | 0.0560331 | 0.887219 | 1(Win) | true |
| Jsonifier (two-stage) | 1993.68 | 0.0502935 | 604.731ms | 11812 | 40 | 323.013 | 5650.25 | 0.11167 | 1.23577 | 2(Loss) | true |
| Glaze | 1900.62 | 0.0809986 | 641.651ms | 11812 | 30 | 691.403 | 5926.9 | 0.0726032 | 1.29713 | 3(Loss) | true |
| simdjson (ondemand) | 1069.9 | 0.264425 | 1128.82ms | 11812 | 320 | 248037 | 10528.9 | 0.0175677 | 2.30812 | 4(Loss) | true |
