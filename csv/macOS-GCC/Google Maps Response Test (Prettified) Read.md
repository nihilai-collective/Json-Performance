
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2316.57 | 0.236161 | 1049.96ms | 25388 | 640 | 389908 | 10451.6 | 0.17252 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2133.26 | 0.089233 | 1142.31ms | 25388 | 4890 | 501567 | 11349.7 | 0.160102 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 2114.65 | 1.56002 | 982.866ms | 25388 | 320 | 1.02092e+07 | 11449.6 | 1.91886 | 2(Tie) | true |
| Glaze | 1708.77 | 0.161886 | 1431.44ms | 25388 | 640 | 336736 | 14169.2 | 0.171908 | 4(Loss) | true |
| simdjson (ondemand) | 1449.2 | 0.0750442 | 1695.8ms | 25388 | 4890 | 768676 | 16707.1 | 0.214045 | 5(Loss) | true |
