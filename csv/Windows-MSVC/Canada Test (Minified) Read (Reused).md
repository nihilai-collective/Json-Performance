
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 708.941 | 1.61412 | 5692.98ms | 2251027 | 80 | 1.91118e+11 | 3.0281e+06 | 0.85667 | 3.49221 | 1(Win) | true |
| Jsonifier (two-stage) | 648.813 | 0.989227 | 5923.32ms | 2251027 | 80 | 8.57048e+10 | 3.30873e+06 | 0.344973 | 3.81587 | 2(Loss) | true |
| simdjson (ondemand) | 207.618 | 0.592902 | 7722.19ms | 2251027 | 40 | 1.50334e+11 | 1.03399e+07 | 0.673995 | 11.9247 | 3(Loss) | true |
| Glaze | 189.875 | 0.793382 | 8578.61ms | 2251027 | 40 | 3.21848e+11 | 1.13061e+07 | 0.2944 | 13.0392 | 4(Loss) | true |
