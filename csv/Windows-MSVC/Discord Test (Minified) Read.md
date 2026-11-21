
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1329.39 | 0.28037 | 4247.16ms | 56369 | 320 | 4.11327e+06 | 40437.8 | 0.162794 | 1.8612 | 1(Win) | true |
| Glaze STATISTICAL TIE | 992.193 | 0.0864684 | 5499.41ms | 56369 | 4890 | 1.07328e+07 | 54180.7 | 0.0814835 | 2.49401 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 989.329 | 0.339351 | 5483.34ms | 56369 | 160 | 5.44022e+06 | 54337.5 | 0.265252 | 2.50152 | 2(Tie) | true |
| simdjson (ondemand) | 785.82 | 0.0789208 | 6858.96ms | 56369 | 4890 | 1.42537e+07 | 68409.7 | 0.591596 | 3.14932 | 4(Loss) | true |
