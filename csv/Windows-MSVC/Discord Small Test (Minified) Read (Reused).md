
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1508.18 | 0.18493 | 366.538ms | 4857 | 80 | 2580.7 | 3071.25 | 0.285714 | 1.62599 | 1(Win) | true |
| Glaze | 1380.83 | 0.35991 | 381.685ms | 4857 | 2560 | 373149 | 3354.49 | 0.0570923 | 1.77734 | 2(Loss) | true |
| Jsonifier (two-stage) | 1108.8 | 0.134492 | 476.99ms | 4857 | 80 | 2525.32 | 4177.5 | 0.0598086 | 2.21932 | 3(Loss) | true |
| simdjson (ondemand) | 869.843 | 0.228537 | 583.975ms | 4857 | 4890 | 724228 | 5325.09 | 0.941479 | 2.83153 | 4(Loss) | true |
