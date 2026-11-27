
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1752.76 | 0.118436 | 7011ms | 409725 | 320 | 2.23077e+07 | 222930 | 0.0489095 | 2.89331 | 14.1906 | 2.70506 | 0.00575057 | 0.0130806 | 1.15931e-05 | 1(Win) | true |
| simdjson (ondemand) | 1229.77 | 0.0445685 | 9453.75ms | 409725 | 1280 | 2.56687e+07 | 317737 | 0.113658 | 4.14654 | 17.047 | 3.12522 | 0.01137 | 0.019866 | 5.25333e-05 | 2(Loss) | true |
